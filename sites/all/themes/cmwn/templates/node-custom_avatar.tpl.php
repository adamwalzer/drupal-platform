<?php switch($_GET['mod'] == 'process' || $_GET['mod'] == 'denied' || $_GET['mod'] == 'approved'): ?>
<?php case true:?>
  <?php include(drupal_get_path('theme','cmwn') . '/templates/node-custom-avatar-moderate.inc'); ?>
  <?php break;?>

<?php default: ?>
  <div id="node-<?php print $node->nid; ?>" class="<?php print $classes; ?> clearfix">
  
    <?php if ($unpublished): ?>
      <div class="unpublished"><?php print t('Unpublished'); ?></div>
    <?php endif; ?>
  
    <div class="content">
      <?php print $content; ?>
    </div>
  
    <?php print $links; ?>
  </div><!-- /.node -->

<?php break;?>

<?php endswitch;?>