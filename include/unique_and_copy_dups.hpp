

namespace mstl
{
    template<typename ForwardIterator
            ,typename OutputIterator
            ,typename Predicate>
    auto unique_and_copy_dups(ForwardIterator    first
                             ,ForwardIterator    last
                             ,OutputIterator     dup
                             ,Predicate       && pred)
        -> std::pair<ForwardIterator, OutputIterator>
    {
        if( first == last )
        {
            return std::make_pair(last, dup);
        }

        auto next   = std::next(first);
        auto unique = first;

        while(first != last)
        {
            *unique = std::move(*first);

            while(next != last && pred(*unique, *next))
            {
                *dup = std::move(*next);
                std::advance(next, 1);
            }

            first = next;
            std::advance(next, 1);
            std::advance(unique, 1);
        }

        return std::make_pair(unique, dup);
    }
}
