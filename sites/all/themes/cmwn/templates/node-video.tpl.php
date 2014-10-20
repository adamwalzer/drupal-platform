<?php
if ($unpublished) :
?>
Your video should be available shortly.
<?php 
else :
$viddler_id = $node->field_viddler_id[0]['safe'];
?>
<?php echo theme('cmwn_module_viddler_video', $viddler_id); ?>
<?php print $links; ?>
<?php endif; ?>