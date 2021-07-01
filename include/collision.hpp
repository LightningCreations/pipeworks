#ifndef PW_COLLISION_HPP_2021_07_01_11_37_57
#define PW_COLLISION_HPP_2021_07_01_11_37_57

#include <type_traits>

#include <execution>
#include <iterator>
#include <algorithm>

namespace pipeworks{
    template<typename T> concept _is_bool = std::is_same_v<std::remove_cv_t<T>,bool>;

    template<typename T> concept _boolean = requires(T t){
        {t&&t} noexcept -> _is_bool;
        {t||t} noexcept -> _is_bool;
        {!t} noexcept -> _is_bool;
        {static_cast<bool>(t)} noexcept;
    };

    template<typename T,typename U> constexpr auto collide_with(const T& t,const U& u) noexcept(noexcept(t.collide_with(u))) -> decltype(t.collide_with(u)){
        return t.collide_with(u);
    }

    /// SEMANTIC:
    /// collide_with(t,t) shall be symmetric and reflexive
    template<typename T> concept collision = requires(const T& t){
        typename T::value_type;

        {collide_with(t,t)} -> _boolean;
    };

    /// SEMANTIC:
    /// collide_with(t,u) shall be symmetric and reflexive
    template<typename T,typename U> concept collideable_with = collision<T>&&collision<U>&&requires(T t,const U& u){
        {collide_with(t,u)} -> _boolean; 
    };

    /// SEMANTIC:
    /// The function collide_with(t,u) shall be vectorization safe.
    template<typename T,typename U> concept vector_collideable_with = collideable_with<T,U>;


    template<typename T> struct PointCollision{
        T x;
        T y;

        constexpr PointCollision()noexcept=default;

        friend constexpr auto operator==(const PointCollision& p1,const PointCollision& p2)  noexcept(noexcept(p1.x==p2.x)) -> decltype(p1.x==p2.x){
            return p1.x==p2.x&&p1.y==p2.y;
        }

        template<typename U>
            friend constexpr auto collide_with(const PointCollision<T>& p1,const PointCollision<U>& p2) noexcept(noexcept(p1.x==p2.x)) -> decltype(p1.x==p2.x){
                return p1.x==p2.x&&p1.y==p2.y;
            }
    };


    template<typename T,typename ForwardIt,typename OutputForwardIt,
        typename ExecutionPolicy,
        std::enable_if_t<std::is_execution_policy_v<ExecutionPolicy>>* =nullptr,
        std::enable_if_t<std::is_base_of_v<std::forward_iterator_tag,typename std::iterator_traits<ForwardIt>::iterator_category>&&std::is_base_of_v<std::forward_iterator_tag,typename std::iterator_traits<OutputForwardIt>::iterator_category>>* =nullptr>
        requires vector_collideable_with<T,typename std::iterator_traits<ForwardIt>::value_type>
        OutputForwardIt collide_all(ExecutionPolicy&& ep, const T& t,ForwardIt begin,ForwardIt end,OutputForwardIt out){
            return std::transform(std::forward<ExecutionPolicy>(ep),begin,end,out,[&t](const auto& a){
                return collide_with(t,a);
            });
        }

}

#endif /* PW_COLLISION_HPP_2021_07_01_11_37_57 */