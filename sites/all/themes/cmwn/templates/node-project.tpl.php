<img src="<?php echo url(drupal_get_path('theme', 'cmwn')); ?>/assets/img/time-to-shine.jpg" style="margin:0 0 0 3px;" />
<?php include 'rounded/rounded-top-cutoff.tpl.php'; ?>
<div id="node-<?php print $node->nid; ?>" class="<?php print $classes; ?> clearfix">
  <!-- <a class="arrow-link print" href="<?php echo url($node->field_action_item[0]['filepath']); ?>"><span></span>Print</a>-->
  <h1 class="dashed"><?php echo $title; ?></h1>
  <h2>Information About the Project</h2>
  <div class="content">
    <?php print $body; ?>
  </div>
</div>
<?php
  if (og_is_group_member($node->nid, true, $user->uid)) {
    require_once drupal_get_path('module', 'node').'/node.pages.inc';
    echo node_add('project_submission');
    ?>
<?php include 'rounded/rounded-bottom-cutoff.tpl.php'; ?>
<img src="<?php echo url(drupal_get_path('theme', 'cmwn')); ?>/assets/img/complete-project.png" style="margin:-6px 0 0 0;" />
<h2 class="upload">Upload</h2>
<h3 class="upload">Browse My Files</h3>
<h2 class="submit">Submit</h2>
<h3 class="submit">Send My Project</h3>
    <script type="text/javascript" src="<?php echo url(drupal_get_path('theme', 'cmwn')); ?>/assets/js/si.files.js"></script>
<script type="text/javascript">
jQuery(function($){
  SI.Files.stylizeById('edit-field-file-0-upload');
  $('#node-form .description').hide();
  $('#node-form label').hide();
  $('#node-form #edit-submit').hide();
  $('#edit-field-file-0-filefield-upload').hide();
  $('.upload').click(function(){
    $('#node-form #edit-field-file-0-upload')[0].click();
  });
  $('.submit').click(function(){
    $('#node-form #edit-submit')[0].click();
  });
});
</script>
<style type="text/css">
.SI-FILES-STYLIZED .filefield-upload
{
  width: 214px;
  height: 32px;
  position:absolute;
  margin:-110px 0 0 439px;  
  background:url('<?php echo url(drupal_get_path('theme', 'cmwn')); ?>/assets/img/transparent.png');
  display: block;
  overflow: hidden;
  cursor: pointer;
}

.SI-FILES-STYLIZED .filefield-upload #edit-field-file-0-upload
{
  position: relative;
  height: 100%;
  width: auto;
  background:red;  
  opacity: 0;
  -moz-opacity: 0;
  filter:progid:DXImageTransform.Microsoft.Alpha(opacity=0);
}


h2.upload,
h2.submit {
  color:#00b1f1;
  font-size:25px;
  margin:0;
  padding:0;
  cursor:pointer;
}
h2.upload {
  position:absolute;
  margin:-132px 0 0 480px;
}
h2.submit {
  position:absolute;
  margin:-132px 0 0 740px;
}
h3.upload,
h3.submit {
  color:#5e5b5b;
  font-size:14px;
  margin:0;
  padding:0;
  cursor:pointer
}
h3.upload {
  position:absolute;
  margin:-89px 0 0 452px;
}
h3.submit {
  position:absolute;
  margin:-89px 0 0 706px;
}
</style>
      <?php 
    } else {
  ?>
<?php include 'rounded/rounded-bottom.tpl.php'; ?>
<?php } ?>