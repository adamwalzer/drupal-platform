<div class="two-col">
  <?php if ($node->field_header_image) : ?>
  <img src="<?php echo url($node->field_header_image[0]['filepath']); ?>" style="margin:0 0 0 -20px;" />
  <?php include 'rounded/rounded-top-cutoff.tpl.php'; ?>
  <?php else : ?>
  <?php include 'rounded/rounded-top.tpl.php'; ?>
  <?php endif; ?>
  <div class="left-sidebar">
  <?php 
  if (module_exists('menu_block')) {
    $menu = menu_tree_build(array(
      'menu_name' => 'primary-links',
      'parent_mlid' => 0,
      'follow' => 1,
      'expanded' => 0,
      'depth' => 2
    ));
    echo $menu['content'];
  }
  ?>
  <ul class="left-buttons">
    <li class="bus-tour"><a href="<?php echo url('bus-tour'); ?>">bus tour</a></li>
    <li class="cool-videos"><a href="<?php echo url('cool-videos'); ?>">cool videos</a></li>
    <li class="news-events"><a href="<?php echo url('events'); ?>">news and events</a></li>
  </ul>
  </div>
  <div id="node-<?php print $node->nid; ?>" class="<?php print $classes; ?> clearfix">
    <h1 class="dashed"><?php echo $title; ?></h1>
    <div class="content">
      <?php print $body; ?>
      <?php
      $block = (object)cmwn_video_block('view', 'upload_video');
      $block->module = 'cmwn_video';
      $block->delta = 'upload_video';
      $block->region = '';
      echo theme('block', $block);
      ?>
    </div>
  </div><!-- /.node -->
  <?php include 'rounded/rounded-bottom.tpl.php'; ?>
</div>