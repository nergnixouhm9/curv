// Copyright Doug Moen 2016-2017.
// Distributed under The MIT License.
// See accompanying file LICENSE.md or https://opensource.org/licenses/MIT

#include <curv/context.h>
#include <curv/eval.h>
#include <curv/file.h>
#include <curv/system.h>

namespace curv {

System_Impl::System_Impl(
    Shared<const String> stdlib_path,
    std::ostream& console)
:
    console_(console)
{
    std_namespace_ = builtin_namespace();
    if (stdlib_path != nullptr) {
        auto file = make<File_Script>(std::move(stdlib_path), Context{});
        Shared<Module> stdlib = eval_module_script(*file, builtin_namespace(), *this);
        for (auto b : *stdlib)
            std_namespace_[b.first] = make<Builtin_Value>(b.second);
    }
}

const Namespace& System_Impl::std_namespace()
{
    return std_namespace_;
}

std::ostream& System_Impl::console()
{
    return console_;
}

} // namespace curv
