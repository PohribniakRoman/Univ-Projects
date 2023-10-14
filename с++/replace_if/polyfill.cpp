template <typename ForwardIt, typename UnaryPredicate, typename T>
void replace_if_polyfill(ForwardIt first, ForwardIt last, UnaryPredicate p, const T& new_value) {
    for (; first != last; ++first) {
        if (p(*first)) {
            *first = new_value;
        }
    }
}