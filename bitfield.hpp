
template<typename X, typename Y>
struct SameType
{
    static constexpr bool result = false; 
};

template<typename X>
struct SameType<X, X>
{
    static constexpr bool result = true; 
};

template<size_t X, size_t Y>
struct GreaterThen
{
    static constexpr bool result = X < Y;
};

template<typename X>
constexpr X getMax(size_t s)
{
    return (1 << s) - 1;
}

template<typename X>
constexpr X getMax()
{
    return ~((X)0);
}

// Enhancements:
// Use Underlying type template to get X (needs to be portable though)
// Have QuickBitStruct (or something) that expects T to be values of E
// Add more control options to Bit field (size, input type, in particular, a mechanim to take signed inputs and shrink them/grow them back to full sized values)
template<typename X, typename E, typename... T>
class BitStruct;

template<typename X, typename E>
class BitStruct<X, E>
{
    protected:
        X data;

    public:
        BitStruct(): data(0) {}
        BitStruct(X initVal): data(initVal) {}

        X get()
        {
            return this->data;
        }

};

template<typename X, typename E, typename Z>
class BitStruct<X, E, Z>: public BitStruct<X, E>
{
    // static_assert(SameType<E, decltype(Z::Pos)>::result, "Type missmatch");

    private:
        constexpr size_t getSize()
        {
            return sizeof(X) - ((size_t)Z::Pos);
        }

    public:
        template<E V>
        void set()
        {
            // static_assert(V == Z::Pos, "Not all enum members are handled");
            if (V == Z::Pos)
            {
                // Error;
                return;
            }
            this->data |= getMax<X>(this->getSize()) << ((X)V);
        }
        template<E V>
        void clear()
        {
            // static_assert(V == Z::Pos, "Not all enum members are handled");
            if (V == Z::Pos)
            {
                // Error;
                return;
            }
            this->data &= ~(getMax<X>(this->getSize()) << ((X)V));
        }
};

template<typename X, typename E, typename Z1, typename Z2, typename... T>
class BitStruct<X, E, Z1, Z2, T...>: public BitStruct<X, E, Z2, T...>
{
    // static_assert(SameType<E, decltype(Z1::Pos)>::result, "Type missmatch");

    private:
        constexpr size_t getSize()
        {
            return ((size_t)Z2::Pos) - ((size_t)Z1::Pos);
        }

    public:
        template<E V>
        void set()
        {
            if (V == Z1::Pos)
            {
                this->data |= getMax<X>(this->getSize()) << ((X)V);
            } 
            else
            {
                BitStruct<X, E, Z2, T...>::template set<V>();
            }
        }
        template<E V>
        void clear()
        {
            if (V == Z1::Pos)
            {
                this->data &= ~(getMax<X>(this->getSize()) << ((X)V));
            }
            else
            {
                BitStruct<X, E, Z2, T...>::template clear<V>();
            }
        }
};

template<typename X, X P>
class BitField
{
    public:
        static constexpr X Pos = P;
};
