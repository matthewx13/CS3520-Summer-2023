#include "Court.h"

Court::Court() {
}

bool Court::reservation_is_free(const Reservation& reservation) const {
    for (const Reservation& r : reservations_) {
        if (r.get_start_time() == reservation.get_start_time() &&
            r.get_end_time() == reservation.get_end_time()) {
            return false;
        }
    }
    return true;
}

void Court::reserve_reservation(const Reservation& reservation) {
    reservations_.push_back(reservation);
}

bool Court::delete_res(int reservation_id) {
    auto it = std::remove_if(reservations_.begin(), reservations_.end(),
                             [&reservation_id](const Reservation& r) {
                                 return r.get_id() == reservation_id;
                             });
    bool removed = it != reservations_.end();
    reservations_.erase(it, reservations_.end());
    return removed;
}

std::vector<Reservation>& Court::get_reservations() {
    return reservations_;
}

const std::vector<Reservation>& Court::get_reservations() const {
    return reservations_;
}


