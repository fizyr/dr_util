// C++
#include <chrono>
#include <ctime>
#include <stdlib.h>

// Catch
#include <catch2/catch.hpp>

// This repository
#include "../src/chrono_ptime.hpp"

namespace dr {

TEST_CASE("timestamp -- system_clock_epoch", "system_clock_epoch") {
	std::time_t epoch = std::chrono::system_clock::to_time_t(std::chrono::system_clock::time_point{});
	std::tm * date = std::gmtime(&epoch);
	REQUIRE(date->tm_year  == 70);
	REQUIRE(date->tm_mon   ==  0);
	REQUIRE(date->tm_mday  ==  1);
	REQUIRE(date->tm_hour  ==  0);
	REQUIRE(date->tm_min   ==  0);
	REQUIRE(date->tm_sec   ==  0);
	REQUIRE(date->tm_yday  ==  0);
	REQUIRE(date->tm_isdst ==  0);
}

TEST_CASE("timestamp -- chrono_ptime_epoch", "chrono_ptime_epoch") {
	boost::posix_time::ptime epoch = toPtime(std::chrono::system_clock::time_point{});
	REQUIRE(epoch.date().year()        == 1970);
	REQUIRE(epoch.date().month()       == 1);
	REQUIRE(epoch.date().day()         == 1);
	REQUIRE(epoch.date().day_of_year() == 1);
	REQUIRE(epoch.time_of_day()        == boost::posix_time::seconds(0));
}

TEST_CASE("timestamp -- chrono_ptime_2017", "chrono_ptime_2017") {

	std::tm tm;
	tm.tm_year = 117;
	tm.tm_mon  = 2;
	tm.tm_mday = 30;
	tm.tm_wday = 4;
	tm.tm_hour = 13;
	tm.tm_min  = 37;
	tm.tm_sec  = 42;

	boost::posix_time::ptime time = toPtime(std::chrono::system_clock::from_time_t(std::mktime(&tm)));

	REQUIRE(time.date().year()           == 2017);
	REQUIRE(time.date().month()          == boost::gregorian::Mar);
	REQUIRE(time.date().day()            == 30);
	REQUIRE(time.date().day_of_year()    == 89);
	REQUIRE(time.date().day_of_week()    == boost::gregorian::Thursday);
	REQUIRE(time.time_of_day().hours()   == 11);
	REQUIRE(time.time_of_day().minutes() == 37);
	REQUIRE(time.time_of_day().seconds() == 42);
}

}
