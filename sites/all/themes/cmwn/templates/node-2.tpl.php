
  <?php if ($node->field_header_image) : ?>
  <img src="<?php echo url($node->field_header_image[0]['filepath']); ?>" style="margin:0 0 0 -20px;" />
  <?php include 'rounded/rounded-top-cutoff.tpl.php'; ?>
  <?php else : ?>
  <?php include 'rounded/rounded-top.tpl.php'; ?>
  <?php endif; ?>
  <div id="node-<?php print $node->nid; ?>" class="<?php print $classes; ?> clearfix">
    <h1 class="dashed"><?php echo $title; ?></h1>
    <form action="" method="get">
      <input class="text" type="text" name="title" value="Search Videos" onfocus="$(this).val() == 'Search Videos' ? $(this).val('') : null" />
      <input class="submit" type="submit" value="" />
    </form>
    <div class="content">
      <?php print $body; ?>
      <?php echo views_embed_view('cool_videos', 'default'); ?>
    </div>
  </div><!-- /.node -->
  <script type="text/javascript">
  jQuery(function($){
    $('.views-field-nothing a').live('click', function(e){
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
  <?php include 'rounded/rounded-bottom.tpl.php'; ?>