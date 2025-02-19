#ifndef PBD_EDGE_LENGTH_CONSTRAINT_H
#define PBD_EDGE_LENGTH_CONSTRAINT_H

#include "constraint.h"

namespace xpbd {

class edge_length_constraint_t : public constraint_t
{
  public:
    using self_type      = edge_length_constraint_t;
    using base_type      = constraint_t;
    using index_type     = std::uint32_t;
    using scalar_type    = double;
    using masses_type    = Eigen::VectorXd;
    using positions_type = typename base_type::positions_type;
    using gradient_type  = typename base_type::gradient_type;

  public:
    edge_length_constraint_t(
        std::initializer_list<index_type> indices,
        positions_type const& p,
        scalar_type const alpha = 0.0)
        : base_type(indices, alpha), d_(0.)
    {
        assert(indices.size() == 2u);
        auto const e0 = this->indices()[0];
        auto const e1 = this->indices()[1];

        d_ = (p.row(e0) - p.row(e1)).norm();
    }

    scalar_type evaluate(positions_type const& V, masses_type const& M) const;
    virtual void
    project(positions_type& V, masses_type const& M, scalar_type& lagrange, scalar_type const dt)
        const override;

  private:
    scalar_type d_; ///< rest length
};

} // namespace xpbd

#endif // PBD_EDGE_LENGTH_CONSTRAINT_H
