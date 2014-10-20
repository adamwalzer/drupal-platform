<?php
if ($user->uid === 0 && arg(1) !== 'password' && arg(1) !== 'reset') {
  drupal_goto('user/login');
}
?>
<?php include 'page/header.tpl.php'; ?>
    <div class="section-wrap">
      <div class="int-nav">
        <?php print $int_nav; ?>
      </div>
      <?php print $messages; ?>
      <?php print $help; ?>
      <?php if ($tabs && in_array('moderator', $user->roles)): ?>
      <div class="tabs"><?php print $tabs; ?></div>
      <?php endif; ?>
      <?php print $content_top; ?>
      <?php print $content; ?>
      <?php print $content_bottom; ?>
      <div class="aside">
        <?php print $sidebar; ?>
      </div>
    </div>
<?php include 'page/footer.tpl.php'; ?>