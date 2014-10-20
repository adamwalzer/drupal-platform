<?php 
$permission = false;
$role = get_role_from_rid(variable_get('cmwn_module_approved_child_role', ''));
$permission = in_array($role, $user->roles)
  || in_array('administrator', $user->roles)
  || in_array('moderator', $user->roles);
?>
<div class="two-col">
  <?php if ($node->field_header_image) : ?>
  <img src="<?php echo url($node->field_header_image[0]['filepath']); ?>" style="margin:0 0 0 -20px;" />
  <?php include 'rounded/rounded-top-cutoff.tpl.php'; ?>
  <?php else : ?>
  <?php include 'rounded/rounded-top.tpl.php'; ?>
  <?php endif; ?>
  <div class="left-sidebar">
  <?php 
  if (module_exists('menu_block')) {
    $menu = menu_tree_build(array(
      'menu_name' => 'primary-links',
      'parent_mlid' => 0,
      'follow' => 1,
      'expanded' => 0,
      'depth' => 2
    ));
    echo $menu['content'];
  }
  ?>
  <ul class="left-buttons">
    <li class="bus-tour"><a href="<?php echo url('bus-tour'); ?>">bus tour</a></li>
    <li class="cool-videos"><a href="<?php echo url('cool-videos'); ?>">cool videos</a></li>
    <li class="news-events"><a href="<?php echo url('events'); ?>">news and events</a></li>
  </ul>
  </div>
  <div id="node-<?php print $node->nid; ?>" class="<?php print $classes; ?> clearfix">
    <h1 class="dashed"><?php echo $title; ?></h1>
    <div class="content">
      <p>Have a question and don’t know where to find the answer?  Send an email or letter to Dear Jack or Dear Jill for their expert advice in all problems, big and small! They’re here to help and are waiting to hear from you!</p>
      <img src="<?php echo url(drupal_get_path('theme', 'cmwn')); ?>/assets/img/dear-jill.jpg" />
      <div class="jill-button-wrap"><a class="jill-button" href="#ask-jill"></a></div>
      <?php echo views_embed_view('jack_jill', 'default', 'jill'); ?>
      <a id="ask-jill" name="ask-jill"></a>
      <?php print $permission ? $body : ''; ?>
    </div>
  </div><!-- /.node -->
  <?php include 'rounded/rounded-bottom.tpl.php'; ?>
</div>