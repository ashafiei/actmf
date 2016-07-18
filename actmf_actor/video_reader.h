/*
 * Actor Multimedia Framework (actmf)
 * Copyright (C) 2016  Arash Shafiei
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * 
 */

#ifndef ACTMF_VIDEO_READER_H
#define ACTMF_VIDEO_READER_H

#include "actmf_interface/abstract_service.h"
#include "tmmp/all.h"

namespace actmf {
  

  
  //  template <class Inspector>
  //typename Inspector::result_type inspect(Inspector& f, AVFrame& x) {
    
    //return f(caf::meta::type_name("AVFrame"), 
    //  x.base, x.best_effort_timestamp,
    //  x.buf, x.buffer_hints, x.channel_layout, x.channels, x.chroma_location,
    //  x.coded_picture_number, x.color_primaries, x.color_range, x.color_trc,
    //  x.colorspace, x.data, x.dct_coeff, x.decode_error_flags, x.display_picture_number,
    //  x.error, x.extended_buf, x.extended_data, x.flags, x.format,
    //  x.height, x.hwaccel_picture_private, x.interlaced_frame,
    //  x.key_frame, x.linesize, x.mb_type, x.mbskip_table, x.metadata,
    //  x.motion_subsample_log2, x.motion_val, x.nb_extended_buf,
    //  x.nb_samples, x.nb_side_data, x.opaque, x.owner, x.palette_has_changed,
    //  x.pan_scan, x.pict_type, x.pkt_dts, x.pkt_duration, x.pkt_pos,
    //  x.pkt_pts, x.pkt_size, x.pts, x.qp_table_buf, x.qscale_table,
    //  x.qscale_type, x.qstride, x.quality, x.ref_index, x.reference,
    //  x.reordered_opaque, x.repeat_pict, x.sample_aspect_ratio,
    //  x.sample_rate, x.side_data, x.thread_opaque, x.top_field_first,
    //  x.type, 
    //	x.width
    //);
  //}
  
  class video_reader : public abstract_service
  {
  private:
    VideoReader * vreader;
    RawFrame data;
  protected:
    virtual caf::behavior awaiting_task();
  public:
    video_reader(caf::actor_config& cfg);
    ~video_reader();
  };
  
  class video_reader_factory : abstract_service_factory
  {
  public:
   virtual caf::actor spawn(caf::actor_system * system);
  };
 
}

#endif // ACTMF_VIDEO_READER_H
