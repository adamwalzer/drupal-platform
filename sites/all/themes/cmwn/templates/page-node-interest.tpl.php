<?php include 'page/header.tpl.php'; ?>
    <div class="section-wrap">
        <div class="pad-wrap">
        <div class="int-nav">
          <?php print $int_nav; ?>
        </div>
        <?php print $messages; ?>
        <?php if ($tabs): ?>
        <div class="tabs"><?php print $tabs; ?></div>
        <?php endif; ?>
        <?php print $help; ?>
        <?php print $content_top; ?>
        <img src="<?php echo url(drupal_get_path('theme', 'cmwn')); ?>/assets/img/section-headers/interested-in.jpg" style="margin:0 0 0 -20px;" />
        <?php include 'rounded/rounded-top-cutoff.tpl.php'; ?>
        <h1 class="dashed"><?php echo $title; ?></h1>
        <?php print $content; ?>
        <?php include 'rounded/rounded-bottom.tpl.php'; ?>
        <?php print $content_bottom; ?>
        <div class="aside">
          <?php print $sidebar; ?>
        </div>
      </div>
    </div>
<?php include 'page/footer.tpl.php'; ?>