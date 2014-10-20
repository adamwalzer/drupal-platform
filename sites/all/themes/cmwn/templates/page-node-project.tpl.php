<?php include 'page/header.tpl.php'; ?>
    <div class="section-wrap">
      <div class="int-nav">
        <?php print $int_nav; ?>
      </div>
      <?php print $messages; ?>
      <?php if ($tabs): ?>
      <div class="tabs"><?php print $tabs; ?></div>
      <?php endif; ?>
      <?php print $help; ?>
      <?php print $content_top; ?>
      <?php print $content; ?>
      <?php print $content_bottom; ?>
      <div class="aside">
        <?php print $sidebar; ?>
      </div>
    </div>
<?php include 'page/footer.tpl.php'; ?>