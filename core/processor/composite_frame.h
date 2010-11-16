#pragma once

#include "frame.h"

#include <memory>
#include <algorithm>

namespace caspar { namespace core {
	
class composite_frame : public frame
{
public:
	composite_frame(const std::vector<frame_ptr>& container);
	composite_frame(const frame_ptr& frame1, const frame_ptr& frame2);

	static frame_ptr interlace(const frame_ptr& frame1,	const frame_ptr& frame2, video_update_format::type mode);
	
private:

	virtual void begin_write();
	virtual void end_write();
	virtual void begin_read();
	virtual void end_read();
	virtual void draw(const frame_shader_ptr& shader);

	struct implementation;
	std::shared_ptr<implementation> impl_;
};
typedef std::shared_ptr<composite_frame> gpu_composite_frame_ptr;
	
}}