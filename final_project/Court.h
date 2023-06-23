#pragma once
#include <vector>
#include "Reservation.h"
#include "User.h"

class Court {
public:
    Court();

    bool is_slot_available(const Reservation& reservation) const;
    void reserve_slot(const Reservation& reservation);
    bool cancel_reservation(int reservation_id);
    const std::vector<Reservation>& get_reservations() const;
    std::vector<Reservation>& get_reservations();

private:
    std::vector<Reservation> reservations_;
};
