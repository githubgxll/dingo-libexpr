// Copyright (c) 2023 dingodb.com, Inc. All Rights Reserved
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "ungrouped_agg_op.h"

namespace dingodb::rel::op {

UngroupedAggOp::UngroupedAggOp(const std::vector<const Agg *> *aggs) : m_aggs(aggs), m_cache(nullptr) {
}

UngroupedAggOp::~UngroupedAggOp() {
  for (const auto *agg : *m_aggs) {
    delete agg;
  }
  delete m_aggs;
  delete m_cache;
}

expr::Tuple *UngroupedAggOp::Put(expr::Tuple *tuple) const {
  if (m_cache == nullptr) {
    m_cache = new expr::Tuple(m_aggs->size());
  }
  for (int i = 0; i < m_aggs->size(); ++i) {
    (*m_cache)[i] = (*m_aggs)[i]->Add((*m_cache)[i], tuple);
  }
  delete tuple;
  return nullptr;
}

}  // namespace dingodb::rel::op
