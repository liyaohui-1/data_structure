/******************************************************************************
 * Copyright 2018 The iDrive Authors. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *****************************************************************************/

#ifndef IROS_BASE_FOR_EACH_H_
#define IROS_BASE_FOR_EACH_H_

#include <type_traits>

#include "iros/base/macros.h"

namespace idrive {
namespace iros {
namespace base {

DEFINE_TYPE_TRAIT(HasLess, operator<)   // NOLINT

template<class Value, class End>
typename std::enable_if<HasLess<Value>::value && HasLess<End>::value, bool>::type
LessThan(const Value& val, const End& end)
{
    return val < end;
}

template<class Value, class End>
typename std::enable_if<!HasLess<Value>::value || !HasLess<End>::value, bool>::type
LessThan(const Value& val, const End& end)
{
    return val != end;
}

#define FOR_EACH(i, begin, end) \
    for (auto i = (true ? (begin) : (end)); idrive::iros::base::LessThan(i, (end)); ++i)

}   // namespace base
}   // namespace iros
}   // namespace idrive

#endif   // IROS_BASE_FOR_EACH_H_
