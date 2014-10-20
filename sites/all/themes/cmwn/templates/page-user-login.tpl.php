<?php include 'page/header.tpl.php'; ?>
    <div class="section-wrap">
      <div class="int-nav">
        <?php print $int_nav; ?>
      </div>
      <?php print $messages; ?>
      <?php print $help; ?>
      <?php print $content_top; ?>
      <div class="user-login-wrap">
      <img class="round" src="<?php echo url(drupal_get_path('theme', 'cmwn')); ?>/assets/img/login-round.png" />
      <img class="bg" src="<?php echo url(drupal_get_path('theme', 'cmwn')); ?>/assets/img/login-bg.jpg" />
      <h1>Login</h1>
      <?php print $content; ?>
      </div>
      <?php print $content_bottom; ?>
      <div class="aside">
        <?php print $sidebar; ?>
      </div>
    </div>
<?php include 'page/footer.tpl.php'; ?>