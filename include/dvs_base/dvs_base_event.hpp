#ifndef DVS_BASE_EVENT
#define DVS_BASE_EVENT

template <typename Ts, typename Coord, typename Polarity>
struct EventBase
{
public:
    /* Event triats */
    typedef Ts TimestampType;
    typedef Coord CoordType;
    typedef Polarity PolarityType;
    /* Trait interface */
    TimestampType ts() { return ts_; }
    CoordType x() { return x_; }
    CoordType y() { return y_; }
    PolarityType polarity() { return polarity_; }
    /* Stored data */
    TimestampType ts_;
    CoordType x_, y_;
    PolarityType polarity_;
};
#endif