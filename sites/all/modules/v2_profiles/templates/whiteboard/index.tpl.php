<?php /* 1.4 */ ?>
<?php
if($user->user_type =='parent' && arg(2) != 'friends' && arg(2) !='children' && arg(2) != 'class'){
  print theme('v2_profiles_resource_center_index', theme('image', 'sites/all/themes/cmwn/assets/img/resource-center-coming-soon.jpg'));
}
?>
<div class="block shadow whiteboard index" id="whiteboard-profile-tabs">
	<ul class="header">
		<li class="section">
      <a href="#whiteboard-tab"><h2>Whiteboard</h2></a>
		</li>

		<li class="section">
      <a href="#newsfeed-tab" class="tab-newsfeed"><h2>News Feed</h2></a><span class="call-monitor" title="Call a Monitor"></span>
		</li>
	</ul>

  <div id="whiteboard-tab">
  	<?php print theme('v2_profiles_whiteboard_tab',$data); ?>
  </div>

  <div id="newsfeed-tab">
    <div class="items">
          <?php //print views_embed_view('newsfeed', 'block_1'); ?>
          <div class="view view-newsfeed">
              <div class="view-content">
                <?php foreach($data->news_items as $news):?>
                  <div class="views-row item">
                    <div class="avatar">
                      <?php 
                        switch($news->type){
                          case 'news':
                            $tid = array_shift($news->taxonomy);
                            print taxonomy_image_display($tid->tid);
                            break;
                          default:
  //                          print_r($news);
                            //whiteboard author
                      			print '<img alt="" height="84" src="'. (v2_profiles_avatars_query($news->field_user_reference[0]['uid'])) . '" width="84" />';
                      			 unset($news->title);
                             $author = user_load($news->field_user_reference[0]['uid']);
                             $news->title = $author->name;
                            break;
                        }
                      ?>
                    </div>
                    <?php print '<h3 class="news-div">' . $news->title . '</h3>'; ?>
                    <?php if($data->readonly == false):?>    
                      <div class="actions">
                      		<a class="delete" href="/user/<?php print arg(1);?>/news/<?php print $news->nid;?>/delete" title="Remove this news">Delete</a>
                      </div>
                    <?php endif;?>
                    
                    <?php 
                      
                      print '<div class="news-image news-div">' . theme('image',$news->field_image[0]['filepath']) . '</div>';
                      print '<div class="news-body news-div">' . $news->body . '</div>';  
                    ?>
                      <hr size="1"/>
                      
                      <?php
                        $flag = flag_get_flag('like');
                        $flag_count = $flag->get_count($news->nid);
                        $flagmsg = t('Be the first to like this post!');
                  
                        $flaggers = db_query('SELECT u.uid, u.name FROM {flag_content} fc join {users} u on u.uid = fc.uid where content_type ="node" and content_id = %d and fid = %d order by timestamp desc', array($news->nid, 12));
                        while($flagger = db_fetch_array($flaggers)){
                          $users[] = l($flagger['name'],'user/' . $uid . '/friends/' . $flagger['uid']);
                        }
                  
                        switch (true){
                          case $flag_count <= 3 && $flag_count > 0:
                            $flagmsg = implode(', ',$users) . ' <em> liked this</em>';
                            break;
                          case 0:
                          case $flag_count == null || $flag_count == false:
                            break;
                          default: //more than three
                            $flagmsg = implode(', ', (array_slice($users, 0, 3))) . ' and <em class="modal-tip" id="modal-tip-'.$news->nid.'">'. theme('item_list',array_slice($users,-2), null,'ul',array('class' => 'morelikes'), 'morelikes-' . $news->nid,'item-list-likes') . ($flag_count-3) . ' others liked this</em>';
                            break;
                        }
                        if($data->readonly == false){
                          print flag_create_link('like', $news->nid) . '<span>&nbsp;&middot;&nbsp;' . $flagmsg. '</span>';
                        }else{
                          print '<span>&nbsp;&middot;&nbsp;' . $flagmsg. '</span>';
                        }
                        

                      ?>
                      <div class="news-comments">
                        <?php 
                          print comment_render($news);
                          if($data->readonly == false){
                            print drupal_get_form('comment_form', array('nid' => $news->nid), 'Comment');
                          }
                        ?>
                      </div>
                      
                    
                    
                    <?php if ($comments): ?>
                      <?php print $comments; ?>
                    <?php endif; ?> 
                  </div>
                <?php endforeach;?>
              </div>
          </div>
    </div>
  </div>
</div>