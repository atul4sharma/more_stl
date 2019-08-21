

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

        // The first element will always be in the unique set.
        auto unique  = first;
        // current points to the second element.
        auto current = ++first;

        while(current != last)
        {
            // If the current item is the same as the last
            // item processed add it to the dups.
            if( pred(*unique, *current) )
            {
                dup = std::move(*current);
                ++dup;
            }
            // The current item is part of a new subgroup.
            else
            {
                ++unique;
                // Assignment is required only if the current item is not
                // next to the last unique value.
                if( unique != current )
                {
                    *unique = std::move(*current);
                }
            }
            ++current;
        }

        return std::make_pair(++unique, dup);
    }
}
