<div class="interests">
<?php foreach ($interests as $interest) : ?>
<?php 
$node = node_load($interest->nid);
//var_dump($node);die;
?>
<?php if ($interest->is_member) : ?>
  <div class="interest-<?php echo $node->nid; ?> interest is_member <?php echo $node->field_my_interests_color[0]['value']; ?>">
    <img src="<?php echo url($node->field_interest_large_image_a[0]['filepath']); ?>" alt="<?php echo $node->title; ?>" />
    <a href="<?php echo url('node/'.$node->nid); ?>"><span><?php echo $node->title; ?></span></a>
  </div>
<?php else : ?>
  <div class="interest-<?php echo $node->nid; ?> interest <?php echo $node->field_my_interests_color[0]['value']; ?>">
    <img src="<?php echo url($node->field_interest_large_image_i[0]['filepath']); ?>" alt="<?php echo $node->title; ?>" />
    <a href="<?php echo url('node/'.$node->nid); ?>"><span><?php echo $node->title; ?></span></a>
  </div>
<?php endif; ?>
<?php endforeach; ?>
</div>