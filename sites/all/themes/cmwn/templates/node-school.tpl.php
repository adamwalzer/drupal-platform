<div id="node-<?php print $node->nid; ?>" class="<?php print $classes; ?> clearfix">
  <div class="content">
    <?php
    global $user;
    if($user->uid == $node->uid){
      print l(t('School Dashboard'), 'school/' . $node->nid . '/dashboard');
    }
    ?>
    <?php print $body; ?>
    <?php echo views_embed_view('school_videos', 'default', $node->nid); ?>
  </div>
</div>
<script type="text/javascript">
jQuery(function($){
  $('.view-school-videos a.overlay').live('click', function(e){
    e.preventDefault();
    var $this = $(this);
    $this.overlay({
      mask: 'black',
      onBeforeLoad: function() {
        var wrap = this.getOverlay().find(".contentWrap");
        wrap.load(this.getTrigger().attr("href"));
      },
      load: true,
      effect: 'apple'
    });
  });
});
</script>
