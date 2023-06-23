#include "Court.h"

Court::Court() {
}

bool Court::is_slot_available(const Reservation& reservation) const {
    for (const Reservation& r : reservations_) {
        if (r.get_start_time() == reservation.get_start_time() &&
            r.get_end_time() == reservation.get_end_time()) {
            return false;
        }
    }
    return true;
}

void Court::reserve_slot(const Reservation& reservation) {
    reservations_.push_back(reservation);
}

// bool Court::add_user_to_reservation(int reservation_id, const User& user) {
//     for (Reservation& r : reservations_) {
//         if (r.get_id() == reservation_id) {
//             r.add_user(user.get_username());
//             return true;
//         }
//     }
//     return false;
// }

// bool Court::remove_user_from_reservation(int reservation_id, const User& user) {
//     for (Reservation& r : reservations_) {
//         if (r.get_id() == reservation_id) {
//             r.remove_user(user.get_username());
//             return true;
//         }
//     }
//     return false;
// }

bool Court::cancel_reservation(int reservation_id) {
    auto it = std::remove_if(reservations_.begin(), reservations_.end(),
                             [&reservation_id](const Reservation& r) {
                                 return r.get_id() == reservation_id;
                             });
    bool removed = it != reservations_.end();
    reservations_.erase(it, reservations_.end());
    return removed;
}

const std::vector<Reservation>& Court::get_reservations() const {
    return reservations_;
}

std::vector<Reservation>& Court::get_reservations() {
    return reservations_;
}

