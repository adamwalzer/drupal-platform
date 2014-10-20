<?php if ($node->field_header_image) : ?>
<img src="<?php echo url($node->field_header_image[0]['filepath']); ?>" style="margin:0 0 0 -20px;" />
<div class="events-button-wrap"><a class="events-button" href="#event-dates"></a></div>
<?php include 'rounded/rounded-top-cutoff.tpl.php'; ?>
<?php else : ?>
<?php include 'rounded/rounded-top.tpl.php'; ?>
<?php endif; ?>
<div id="node-<?php print $node->nid; ?>" class="<?php print $classes; ?> clearfix">
  <div class="content">
    <a id="event-dates" name="event-dates"></a>
    <?php print $body; ?>
  </div>
</div><!-- /.node -->
<?php include 'rounded/rounded-bottom.tpl.php'; ?>