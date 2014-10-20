
<div class="interests">
<?php for ($i = 0; $i < count($interests); $i++) : ?>
<?php
if ($interests[$i]->is_member) {
  $path = $interests[$i]->small_image_active;
} else {
  $path = $interests[$i]->small_image_inactive;
}
?>
  <div class="interest<?php echo $i == 0 ? ' first' : ($i == count($interests) - 1 ? ' last' : ''); ?>">
    <a title="<?php echo $interests[$i]->title; ?>" href="<?php echo url('node/'.$interests[$i]->nid); ?>"><?php echo theme('imagecache', 'my_interests', $path)?></a>
  </div>
<?php endfor; ?>
</div>