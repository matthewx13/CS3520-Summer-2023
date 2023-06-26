#pragma once
#include <vector>
#include "Reservation.h"
#include "User.h"

class Court {
public:
    Court();

    bool reservation_is_free(const Reservation& reservation) const;
    void reserve_reservation(const Reservation& reservation);
    bool delete_res(int reservation_id);
    const std::vector<Reservation>& get_reservations() const;
    std::vector<Reservation>& get_reservations();

private:
    std::vector<Reservation> reservations_;
};