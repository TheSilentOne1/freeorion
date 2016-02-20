// -*- C++ -*-
#ifndef _Supply_h_
#define _Supply_h_

#include "../util/Export.h"

#include <boost/serialization/access.hpp>

#include <map>
#include <set>

/** Used to calcuate all empires' supply distributions. */
class FO_COMMON_API SupplyManager {
public:
    /** \name Structors */ //@{
    SupplyManager();
    SupplyManager& operator=(const SupplyManager& rhs);
    //@}

    /** \name Accessors */ //@{
    /** Returns set of directed starlane traversals along which supply can flow.
      * Results are pairs of system ids of start and end system of traversal. */
    const std::map<int, std::set<std::pair<int, int> > >&   SupplyStarlaneTraversals() const;
    const std::set<std::pair<int, int> >&                   SupplyStarlaneTraversals(int empire_id) const;

    /** Returns set of directed starlane traversals along which supply could
      * flow for this empire, but which can't due to some obstruction in one
      * of the systems. */
    const std::map<int, std::set<std::pair<int, int> > >&   SupplyObstructedStarlaneTraversals() const;
    const std::set<std::pair<int, int> >&                   SupplyObstructedStarlaneTraversals(int empire_id) const;

    /** Returns set of system ids where fleets can be supplied by this empire
      * (as determined by object supply meters and rules of supply propagation
      * and blockade). */
    const std::map<int, std::set<int> >&                    FleetSupplyableSystemIDs() const;
    const std::set<int>&                                    FleetSupplyableSystemIDs(int empire_id);

    /** Returns set of sets of systems that can share industry (systems in
      * separate groups are blockaded or otherwise separated). */
    const std::map<int, std::set<std::set<int> > >&         ResourceSupplyGroups() const;
    const std::set<std::set<int> >&                         ResourceSupplyGroups(int empire_id) const;

    /** Returns true if system with id \a system_id is fleet supplyable or in
      * one of the resource supply groups for empire with id \a empire_id */
    bool    SystemHasFleetSupply(int system_id, int empire_id) const;
    //@}

    /** \name Mutators */ //@{
    /** Calculates systems at which fleets of empires can be supplied, and
      * groups of systems that can exchange resources, and the starlane
      * traversals used to do so. */
    void    Update();
    //@}

private:
    /** ordered pairs of system ids between which a starlane runs that can be
        used to convey resources between systems. indexed first by empire id. */
    std::map<int, std::set<std::pair<int, int> > >  m_supply_starlane_traversals;

    /** ordered pairs of system ids between which a starlane could be used to
        convey resources between system, but is not because something is
        obstructing the resource flow.  That is, the resource flow isn't limited
        by range, but by something blocking its flow. */
    std::map<int, std::set<std::pair<int, int> > >  m_supply_starlane_obstructed_traversals;

    /** ids of systems where fleets can be resupplied. indexed by empire id. */
    std::map<int, std::set<int> >                   m_fleet_supplyable_system_ids;

    /** sets of system ids that are connected by supply lines and are able to
        share resources between systems or between objects in systems. indexed
        by empire id. */
    std::map<int, std::set<std::set<int> > >        m_resource_supply_groups;
};

#endif // _Supply_h_
