<?php include 'page/header.tpl.php'; ?>
    <div class="section-wrap">
      <div class="int-nav">
        <?php print $int_nav; ?>
      </div>
      <?php print $messages; ?>
      <?php print $help; ?>
      <?php print $content_top; ?>
      <div class="two-col">
        <?php include 'rounded/rounded-top.tpl.php'; ?>
        <div class="left-sidebar">
          <?php include 'page/page-user-edit-menu.tpl.php'; ?>
        </div>
        <div class="main-content">
          <h1 class="dashed">Pick Avatar</h1>
          <?php print $content; ?>
        </div>
        <?php include 'rounded/rounded-bottom.tpl.php'; ?>
      </div>
      <?php print $content_bottom; ?>
      <div class="aside">
        <?php print $sidebar; ?>
      </div>
    </div>
<?php include 'page/footer.tpl.php'; ?>