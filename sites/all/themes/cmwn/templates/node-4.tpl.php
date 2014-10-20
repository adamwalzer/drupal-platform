<?php if ($node->field_header_image) : ?>
<img src="<?php echo url($node->field_header_image[0]['filepath']); ?>" style="margin:0 0 0 -20px;" />
<div class="bus-tour-button-wrap"><a class="bus-tour-button" href="#tour-dates"></a></div>
<?php endif; ?>
<p>Change My World Now is going on the road! We’re celebrating the global release of the award-winning, best-selling children’s book Cassandra’s Angel. Partnering with Sterling Publishing, we hope to see you on our national 20 city/20 week tour!</p>
<div id="node-<?php print $node->nid; ?>" class="<?php print $classes; ?> clearfix">
  <div class="content">
    <a id="tour-dates" name="tour-dates"></a>
    <?php print $body; ?>
  </div>
</div><!-- /.node -->