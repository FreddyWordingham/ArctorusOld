/**
 *  @author Freddy Wordingham
 *  @email  fjmw201@exeter.ac.uk
 *
 *  @date   07/03/2018.
 */



//  == HEADER ==
#include "cls/tree/cell.hpp"



//  == INCLUDES ==
//  -- System --



//  == NAMESPACE ==
namespace arc
{
    namespace tree
    {



        //  == INSTANTIATION ==
        //  -- Constructors --
        /**
         *  Construct a root cell to record a given list of entity, light, ccd and spectrometer objects.
         *  Tree will reproduce until at least the minimum depth has been reached.
         *  Tree will stop reproducing until either the maxmium depth is reached, or the target maximum number of triangles has
         *  been reached.
         *
         *  @param  t_min_bound     Minimum spatial bound of the cell.
         *  @param  t_max_bound     Maximum spatial bound of the cell.
         *  @param  t_min_depth     Minimum depth for the cell to split to.
         *  @param  t_max_depth     Maximum depth for the cell to split to.
         *  @param  t_entity        Vector of entity objects which may lie within the cell.
         *  @param  t_light         Vector of light objects which may lie within the cell.
         *  @param  t_ccd           Vector of ccd objects which may lie within the cell.
         *  @param  m_spectrometer  Vector of spectrometer objects which may lie within the cell.
         *
         *  @post   m_half_width[X] must be positive.
         *  @post   m_half_width[Y] must be positive.
         *  @post   m_half_width[Z] must be positive.
         */
        Cell::Cell(const math::Vec<3>& t_min_bound, const math::Vec<3>& t_max_bound, const unsigned int t_min_depth,
                   const unsigned int t_max_depth, const std::vector<equip::Entity>& t_entity,
                   const std::vector<equip::Light>& t_light, const std::vector<detector::Ccd>& t_ccd,
                   const std::vector<detector::Spectrometer>& m_spectrometer) :
            m_center((t_max_bound + t_min_bound) / 2.0),
            m_half_width((t_max_bound - t_min_bound) / 2.0),
            m_entity(t_entity)
        {
            assert(m_half_width[X] > 0.0);
            assert(m_half_width[Y] > 0.0);
            assert(m_half_width[Z] > 0.0);
        }


        //  -- Initialisation --



    } // namespace tree
} // namespace arc
