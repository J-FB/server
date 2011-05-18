/*
* copyright (c) 2010 Sveriges Television AB <info@casparcg.com>
*
*  This file is part of CasparCG.
*
*    CasparCG is free software: you can redistribute it and/or modify
*    it under the terms of the GNU General Public License as published by
*    the Free Software Foundation, either version 3 of the License, or
*    (at your option) any later version.
*
*    CasparCG is distributed in the hope that it will be useful,
*    but WITHOUT ANY WARRANTY; without even the implied warranty of
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*    GNU General Public License for more details.

*    You should have received a copy of the GNU General Public License
*    along with CasparCG.  If not, see <http://www.gnu.org/licenses/>.
*
*/
#pragma once

#include <common/memory/safe_ptr.h>
#include <core/producer/frame/basic_frame.h>
#include <core/producer/frame/frame_visitor.h>
#include <core/producer/frame/pixel_format.h>

#include "gpu/host_buffer.h"

#include <boost/noncopyable.hpp>
#include <boost/range/iterator_range.hpp>

#include <memory>
#include <vector>

namespace caspar { namespace core {
	
class write_frame : public core::basic_frame, boost::noncopyable
{
public:	
	explicit write_frame(int tag, const core::pixel_format_desc& desc, const std::vector<safe_ptr<host_buffer>>& buffers);
			
	// core::write_frame
	virtual boost::iterator_range<unsigned char*> image_data(size_t plane_index = 0);	
	virtual std::vector<short>& audio_data();
	
	virtual const boost::iterator_range<const unsigned char*> image_data(size_t plane_index = 0) const;
	virtual const boost::iterator_range<const short*> audio_data() const;

	virtual void accept(core::frame_visitor& visitor);

	virtual int tag() const;
	
private:
	friend class image_mixer;

	const core::pixel_format_desc& get_pixel_format_desc() const;
	const std::vector<safe_ptr<host_buffer>>& get_plane_buffers() const;

	struct implementation;
	std::shared_ptr<implementation> impl_;
};
typedef std::shared_ptr<write_frame> write_frame_impl_ptr;


}}