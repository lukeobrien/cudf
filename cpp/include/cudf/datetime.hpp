/*
 * Copyright (c) 2019, NVIDIA CORPORATION.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef DATETIME_HPP
#define DATETIME_HPP

#include "cudf.h"
#include <functional>
#include <cudf/column/column.hpp>
#include <cudf/column/column_view.hpp>

namespace cudf {
namespace datetime {
namespace detail {

  /**
   * @brief Compare the input time units and returns whichever is more granular,
   * i.e. the gdf_time_unit that can represent the highest precision timestamps.
   * 
   * @returns gdf_time_unit the more granular of the two input gdf_time_units.
   */
  gdf_time_unit common_resolution(gdf_time_unit lhs_unit, gdf_time_unit rhs_unit);

} // namespace detail

/**
 * @brief Ensures GDF_DATE64 or GDF_TIMESTAMP columns share the same time unit.
 * 
 * If they don't, this function casts the values of the less granular column
 * to the more granular time unit. This creates an intermediate gdf_column which
 * must be freed by the caller.
 * 
 * If the time units are the same, or either column's dtype isn't GDF_DATE64 or
 * GDF_TIMESTAMP, no cast is performed and both returned columns will be empty.
 * 
 * @note This method treats GDF_DATE64 columns like GDF_TIMESTAMP[ms]
 *
 * @param[in] gdf_column* lhs column to compare against rhs
 * @param[in] gdf_column* rhs column to compare against lhs
 *
 * @returns std::pair<gdf_column, gdf_column> pair of gdf_columns corresponding to the input cols.
 * If a column was cast, the corresponding pair will be a new intermediate gdf_column, which must
 * be freed by the caller.
 */
std::pair<gdf_column, gdf_column> cast_to_common_resolution(gdf_column const& lhs, gdf_column const& rhs);

/**
 * @brief  Extracts year from any date time type and returns an int16_t cudf::column
 *
 * @param[in] cudf::column_view of the input datetime values
 *
 * @returns cudf::column of the extracted int16_t years
 */
std::unique_ptr<cudf::column> extract_year(cudf::column_view const& column, cudaStream_t stream = 0);

/**
 * @brief  Extracts month from any date time type and returns an int16_t cudf::column
 *
 * @param[in] cudf::column_view of the input datetime values
 *
 * @returns cudf::column of the extracted int16_t months
 */
std::unique_ptr<cudf::column> extract_month(cudf::column_view const& column, cudaStream_t stream = 0);

/**
 * @brief  Extracts day from any date time type and returns an int16_t cudf::column
 *
 * @param[in] cudf::column_view of the input datetime values
 *
 * @returns cudf::column of the extracted int16_t days
 */
std::unique_ptr<cudf::column> extract_day(cudf::column_view const& column, cudaStream_t stream = 0);

/**
 * @brief  Extracts day from any date time type and returns an int16_t cudf::column
 *
 * @param[in] cudf::column_view of the input datetime values
 *
 * @returns cudf::column of the extracted int16_t days
 */
std::unique_ptr<cudf::column> extract_weekday(cudf::column_view const& column, cudaStream_t stream = 0);

/**
 * @brief  Extracts hour from either GDF_DATE64 or GDF_TIMESTAMP type and returns an int16_t cudf::column
 *
 * @param[in] cudf::column_view of the input datetime values
 *
 * @returns cudf::column of the extracted int16_t hours
 */
std::unique_ptr<cudf::column> extract_hour(cudf::column_view const& column, cudaStream_t stream = 0);

/**
 * @brief  Extracts minute from either GDF_DATE64 or GDF_TIMESTAMP type and returns an int16_t cudf::column
 *
 * @param[in] cudf::column_view of the input datetime values
 *
 * @returns cudf::column of the extracted int16_t minutes
 */
std::unique_ptr<cudf::column> extract_minute(cudf::column_view const& column, cudaStream_t stream = 0);

/**
 * @brief  Extracts second from either GDF_DATE64 or GDF_TIMESTAMP type and returns an int16_t cudf::column
 *
 * @param[in] cudf::column_view of the input datetime values
 *
 * @returns cudf::column of the extracted int16_t seconds
 */
std::unique_ptr<cudf::column> extract_second(cudf::column_view const& column, cudaStream_t stream = 0);

}  // namespace datetime
}  // namespace cudf

#endif  // DATETIME_HPP
