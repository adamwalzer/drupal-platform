<div id="node-<?php print $node->nid; ?>" class="<?php print $classes; ?> clearfix">
  <div class="content">
    <?php echo $picture; ?>
    <div class="body">
      <h3><?php echo $title; ?></h3>
      <div class="submitted"><?php echo $submitted; ?></div>
    <?php print $body; ?>
    <?php print $links; ?>
    </div>
  </div>
</div><!-- /.node -->