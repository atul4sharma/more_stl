

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

        auto unique = first;
        auto next   = first;

        while(first != last)
        {
            std::advance(next, 1);
            *unique = std::move(*first);

            while(next != last && pred(*unique, *next))
            {
                *dup = std::move(*next);
                // cannot call std::advance here as dup may be a back_insert_iterator
                // and std::advance does not work with a back_insert_iterator since it
                // does not define a difference_type
                ++dup;
                std::advance(next, 1);
            }

            first = next;
            std::advance(unique, 1);
        }

        return std::make_pair(unique, dup);
    }
}
