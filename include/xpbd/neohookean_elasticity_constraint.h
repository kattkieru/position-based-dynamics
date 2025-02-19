#ifndef PBD_XPBD_NEOHOOKEAN_ELASTICITY_CONSTRAINT_H
#define PBD_XPBD_NEOHOOKEAN_ELASTICITY_CONSTRAINT_H

#include "xpbd/constraint.h"

namespace xpbd {

class neohookean_elasticity_constraint_t : public constraint_t
{
  public:
    using self_type      = neohookean_elasticity_constraint_t;
    using base_type      = constraint_t;
    using index_type     = std::uint32_t;
    using scalar_type    = typename constraint_t::scalar_type;
    using masses_type    = Eigen::VectorXd;
    using positions_type = typename base_type::positions_type;
    using gradient_type  = typename base_type::gradient_type;

  public:
    neohookean_elasticity_constraint_t(
        std::initializer_list<index_type> indices,
        positions_type const& p,
        scalar_type young_modulus,
        scalar_type poisson_ratio,
        scalar_type const alpha = 0.0);

    virtual void
    project(positions_type& p, masses_type const& m, scalar_type& lagrange, scalar_type const dt)
        const override;

  protected:
    scalar_type signed_volume(positions_type const& V) const;

  private:
    scalar_type V0_;
    Eigen::Matrix3d DmInv_;
    scalar_type mu_;
    scalar_type lambda_;
};

} // namespace xpbd

#endif // PBD_XPBD_NEOHOOKEAN_ELASTICITY_CONSTRAINT_H