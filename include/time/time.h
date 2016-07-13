/*!
    \file time.h
    \brief Time wrapper definition
    \author Ivan Shynkarenka
    \date 12.07.2016
    \copyright MIT License
*/

#ifndef CPPCOMMON_TIME_TIME_H
#define CPPCOMMON_TIME_TIME_H

#include "time/timestamp.h"

namespace CppCommon {

//! Time
/*!
    Time wraps date & time in a single object with a set of accessors - year, month, day,
    hours, minutes, seconds, milliseconds, microseconds or nanoseconds.

    32 bit: time is limited in range 1970-01-01T00:00:00Z - 2038-01-18T23:59:59Z
    64 bit: time is limited in range 1970-01-01T00:00:00Z - 3000-12-31T23:59:59Z

    Not thread-safe.
*/
class Time
{
public:
    //! Initialize time with a current date & time values as local or UTC
    /*!
        \param localtime - Local time flag (default is true)
    */
    Time(bool localtime = true) : Time(Timestamp(), localtime) {}
    //! Initialize time with a given timestamp as local or UTC
    /*!
        \param timestamp - Timestamp
        \param localtime - Local time flag (default is true)
    */
    explicit Time(const Timestamp& timestamp, bool localtime = true);
    //! Initialize time with a given date & time components (year, month, day, hour, minute, second, etc.)
    /*!
        \param year - Year value (1970-2038 for 32 bits or 1970-3000 for 64 bits)
        \param month - Month value (1-12)
        \param day - Day value (1-31)
        \param hour - Hour value (0-23) (default is 0)
        \param minute - Minute value (0-59) (default is 0)
        \param second - Second value (0-59) (default is 0)
        \param millisecond - Millisecond value (0-999) (default is 0)
        \param microsecond - Microsecond value (0-999) (default is 0)
        \param nanosecond - Nanosecond value (0-999) (default is 0)
        \param localtime - Local time flag (default is false)
    */
    explicit Time(int year, int month, int day, int hour = 0, int minute = 0, int second = 0, int millisecond = 0, int microsecond = 0, int nanosecond = 0);
    Time(const Time&) noexcept = default;
    Time(Time&&) noexcept = default;
    ~Time() noexcept = default;

    Time& operator=(const Timestamp& timestamp)
    { return operator=(Time(timestamp)); }
    Time& operator=(const Time&) noexcept = default;
    Time& operator=(Time&&) noexcept = default;

    Time& operator+=(const Timespan& offset)
    { return operator=(Time(timestamp() + offset)); }

    Time& operator-=(const Timespan& offset)
    { return operator=(Time(timestamp() - offset)); }

    friend Time operator+(const Time& time, const Timespan& offset)
    { return Time(time.timestamp() + offset); }
    friend Time operator+(const Timespan& offset, const Time& time)
    { return Time(offset + time.timestamp()); }

    friend Time operator-(const Time& time, const Timespan& offset)
    { return Time(time.timestamp() - offset); }
    friend Time operator-(const Timespan& offset, const Time& time)
    { return Time(offset - time.timestamp()); }

    friend Timespan operator-(const Time& time1, const Time& time2)
    { return time1.timestamp() - time2.timestamp(); }

    friend bool operator==(const Time& time, const Timestamp& timestamp)
    { return time.timestamp() == timestamp; }
    friend bool operator==(const Timestamp& timestamp, const Time& time)
    { return timestamp == time.timestamp(); }
    friend bool operator==(const Time& time1, const Time& time2) noexcept;

    friend bool operator!=(const Time& time, const Timestamp& timestamp)
    { return time.timestamp() != timestamp; }
    friend bool operator!=(const Timestamp& timestamp, const Time& time)
    { return timestamp != time.timestamp(); }
    friend bool operator!=(const Time& time1, const Time& time2) noexcept;

    friend bool operator>(const Time& time, const Timestamp& timestamp)
    { return time.timestamp() > timestamp; }
    friend bool operator>(const Timestamp& timestamp, const Time& time)
    { return timestamp > time.timestamp(); }
    friend bool operator>(const Time& time1, const Time& time2) noexcept;

    friend bool operator<(const Time& time, const Timestamp& timestamp)
    { return time.timestamp() < timestamp; }
    friend bool operator<(const Timestamp& timestamp, const Time& time)
    { return timestamp < time.timestamp(); }
    friend bool operator<(const Time& time1, const Time& time2) noexcept;

    friend bool operator>=(const Time& time, const Timestamp& timestamp)
    { return time.timestamp() >= timestamp; }
    friend bool operator>=(const Timestamp& timestamp, const Time& time)
    { return timestamp >= time.timestamp(); }
    friend bool operator>=(const Time& time1, const Time& time2) noexcept;

    friend bool operator<=(const Time& time, const Timestamp& timestamp)
    { return time.timestamp() <= timestamp; }
    friend bool operator<=(const Timestamp& timestamp, const Time& time)
    { return timestamp <= time.timestamp(); }
    friend bool operator<=(const Time& time1, const Time& time2) noexcept;

    //! Convert date & time to the std::chrono time point
    std::chrono::time_point<std::chrono::system_clock, std::chrono::duration<uint64_t, std::nano>> chrono() const
    { return timestamp().chrono(); }
    //! Convert std::chrono time point to date & time
    template <class Clock, class Duration>
    static Time chrono(const std::chrono::time_point<Clock, Duration>& time_point)
    { return Time(Timestamp::chrono(time_point)); }

    //! Get year value (1970-2038 for 32 bits or 1970-3000 for 64 bits)
    int year() const noexcept { return _year; }
    //! Get month value (1-12)
    int month() const noexcept { return _month; }
    //! Get day value (1-31)
    int day() const noexcept { return _day; }
    //! Get hour value (0-23)
    int hour() const noexcept { return _hour; }
    //! Get minute value (0-59)
    int minute() const noexcept { return _minute; }
    //! Get second value (0-59)
    int second() const noexcept { return _second; }
    //! Get millisecond value (0-999)
    int millisecond() const noexcept { return _millisecond; }
    //! Get microsecond value (0-999)
    int microsecond() const noexcept { return _microsecond; }
    //! Get nanosecond value (0-999)
    int nanosecond() const noexcept { return _nanosecond; }

    //! Get timestamp from the current date & time value
    Timestamp timestamp() const;

    //! Get the epoch date & time
    /*!
        Thread-safe.

        \return Epoch date & time
    */
    static Time epoch()
    { return Time(1970, 1, 1); }

    //! Get the current date & time as local time
    /*!
        Thread-safe.

        \return Current date & time as local time
    */
    static Time local()
    { return Time(Timestamp(), true); }

    //! Get the current date & time as UTC time
    /*!
        Thread-safe.

        \return Current date & time as UTC time
    */
    static Time utc()
    { return Time(Timestamp(), false); }

private:
    int _year;
    int _month;
    int _day;
    int _hour;
    int _minute;
    int _second;
    int _millisecond;
    int _microsecond;
    int _nanosecond;
};

/*! \example time_time.cpp Time wrapper example */

} // namespace CppCommon

#include "time.inl"

#endif // CPPCOMMON_TIME_TIME_H
