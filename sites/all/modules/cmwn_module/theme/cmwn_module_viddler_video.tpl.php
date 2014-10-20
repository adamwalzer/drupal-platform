<!--[if IE]>
<object width="437" height="370" id="viddlerOuter-<?php echo $video_id; ?>" classid="clsid:D27CDB6E-AE6D-11cf-96B8-444553540000">
  <param name="movie" value="//www.viddler.com/simple/<?php echo $video_id; ?>/">
  <param name="allowScriptAccess" value="always">
  <param name="allowNetworking" value="all">
  <param name="allowFullScreen" value="true">
  <param name="flashVars" value="f=1&autoplay=f&disablebranding=1&loop=0&nologo=1&hd=0">
  <object id="viddlerInner-<?php echo $video_id; ?>">
    <video id="viddlerVideo-<?php echo $video_id; ?>" src="//www.viddler.com/file/<?php echo $video_id; ?>/html5mobile/" type="video/mp4" width="437" height="350" poster="//www.viddler.com/thumbnail/<?php echo $video_id; ?>/" controls="controls" x-webkit-airplay="allow"></video>
  </object>
</object>
<![endif]-->
<!--[if !IE]>
<!-->
<object width="437" height="370" id="viddlerOuter-<?php echo $video_id; ?>" type="application/x-shockwave-flash" data="//www.viddler.com/simple/<?php echo $video_id; ?>/">
  <param name="movie" value="//www.viddler.com/simple/<?php echo $video_id; ?>/">
  <param name="allowScriptAccess" value="always">
  <param name="allowNetworking" value="all">
  <param name="allowFullScreen" value="true">
  <param name="flashVars" value="f=1&autoplay=t&disablebranding=1&loop=0&nologo=1&hd=0">
  <object id="viddlerInner-<?php echo $video_id; ?>">
    <video id="viddlerVideo-<?php echo $video_id; ?>" src="//www.viddler.com/file/<?php echo $video_id; ?>/html5mobile/" type="video/mp4" width="437" height="350" poster="//www.viddler.com/thumbnail/<?php echo $video_id; ?>/" controls="controls" x-webkit-airplay="allow" autoplay="autoplay"></video>
  </object>
</object>
<!--<![endif]-->