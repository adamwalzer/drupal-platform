<script type="text/javascript">
jQuery(function($){
  $('#submit_info').click(function(e){
    e.preventDefault();
    $('#edit-submit')[0].click();
  });
});
</script>
<div class="title-wrapper">
  <h1>Create a Profile:</h1>
  <h2 class="active">Step 1: Your Info (the requirements)</h2>
  <div class="separator"></div>
  <h2>Step 2: Your Interest Survey (the fun stuff)</h2>
</div>
<div class="wrapper">
<?php
echo drupal_render($form['field_first_name']);
echo drupal_render($form['field_last_name']);
echo drupal_render($form['name']);
echo drupal_render($form['pass']);
echo drupal_render($form['mail']);
echo drupal_render($form['parent_email']);
echo drupal_render($form['field_dob']);
echo drupal_render($form['school_code']);
echo drupal_render($form['field_state']);
echo drupal_render($form['field_country']);
?>
<a class="button blue" id="submit_info" href=""><span>Submit My Info</span></a>
<?php
echo drupal_render($form['submit']);
?>
<?php
echo drupal_render($form);
?>
</div>
<div class="grown-up">
<img src="<?php echo url(drupal_get_path('theme', 'cmwn').'/assets/img/survey/grown-up.jpg'); ?>" />
<a href="<?php echo url('user/register/parent'); ?>" class="parent">Parent</a>
<a href="<?php echo url('user/register/teacher'); ?>" class="teacher">Teacher</a>
</div>