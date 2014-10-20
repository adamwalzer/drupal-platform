<div id="node-<?php print $node->nid; ?>" class="<?php print $classes; ?> clearfix">
  <img src="<?php echo url(drupal_get_path('theme', 'cmwn').'/assets/img/403.jpg'); ?>" style="margin:0 0 0 -20px;" />
  <div class="content">
    <?php print $body; ?>
  </div>
</div><!-- /.node -->