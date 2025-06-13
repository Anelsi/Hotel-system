#pragma once
namespace EnumClasses {
    enum class RoomType {
        Single,
        Double,
        Apartment,
        Deluxe,
        Conference
    };

    enum class Status {
        Available,
        Reserved,
        underRenovation

    };
    enum class OccupancyLevel {
        Low,
        Medium,
        High
    };
    enum class Season {
        Spring,
        Summer,
        Autumn,
        Winter
    };
    enum class DayOfWeek {
        Monday,
        Tuesday,
        Wednesday,
        Thursday,
        Friday,
        Saturday,
        Sunday
    };
    enum class GuestStatus {
        Gold,
        Platinium,
        Regular
    };
    static const int MAX_NUMBERS = 10;
    static const int MAX_RESERVATIONS = 100;
    static const int MAX_CAPACITY = 200;
}

enum class Role {
    Receptionist,
    Accountant,
    Manager

};