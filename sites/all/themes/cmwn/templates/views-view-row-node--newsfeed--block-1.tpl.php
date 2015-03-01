<?php
/**
 * @file views-view-row-node.tpl.php
 * Default simple view template to display a single node.
 *
 * Rather than doing anything with this particular template, it is more
 * efficient to use a variant of the node.tpl.php based upon the view,
 * which will be named node-view-VIEWNAME.tpl.php. This isn't actually
 * a views template, which is why it's not used here, but is a template
 * 'suggestion' given to the node template, and is used exactly
 * the same as any other variant of the node template file, such as
 * node-NODETYPE.tpl.php
 *
 * @ingroup views_templates
 */
 $fnode = node_load($row->nid);
// print_r($fnode->taxonomy[0]);
 //print $node;
?>
<div class="avatar no-shadow">
  <?php $tid = array_shift($fnode->taxonomy);
    print taxonomy_image_display($tid->tid);
  ?>
</div>
<?php print '<h3 class="news-div">' . $fnode->title . '</h3>'; ?>

<div class="actions">
		<a class="delete" href="/user/<?php print arg(1);?>/news/<?php print $fnode->nid;?>/delete" title="Remove this news">Delete</a>
</div>

<?php 
  
  print '<div class="news-image news-div">' . theme('image',$fnode->field_image[0]['filepath']) . '</div>';
  print '<div class="news-body news-div">' . $fnode->body . '</div>';  
?>
  <hr size="1"/>
  
  <?php
    $rndswitch = rand(0,1);
    
    $flag = flag_get_flag('like');
    $flags = $flag->get_count($fnode->nid);
    $flagmsg = t('Be the first to like this post!');    
    switch (true){
      case $flags < 3 && $flags > 0:
        $flagmsg = 'ArtLax20, GSparkles, SoccerC8_784357 and <em>'.$flags.' others liked this</em>';
        break;
      case 0:
        break;
      default: // a few flags less than three
        $flagmsg = t('ArtLax20, GSparkles, SoccerC8_784357 <em> liked this</em>');
        break;
    }
    print flag_create_link('like', $fnode->nid);
    print '<span>&nbsp;&middot;&nbsp;' . $flagmsg. '</span>';

  ?>
  <div class="news-comments">
    <?php 
      print comment_render($fnode);
      print drupal_get_form('comment_form', array('nid' => $fnode->nid), 'Comment');
    ?>
  </div>
  


<?php if ($comments): ?>
  <?php print $comments; ?>
<?php endif; ?> 