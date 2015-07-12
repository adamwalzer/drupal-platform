<?php 
  global $user;
  if(!$user->user_type){
    if(in_array('School Administrator', ($user->roles))){
      $user->user_type = 'School Administrator';
    }
  }
  
  if (
      ($data->readonly == false)
       && 
      (arg(2) != 'school' && ($user->user_type == 'School Administrator' || $user->user_type == 'child' || $user->user_type == 'parent' || $user->user_type == 'teacher'))) { ?>
  		<div class="create">
  			<div class="avatar">
  				<img src="<?php print v2_profiles_avatars_query($user->uid); ?>" width="84" />
  			</div>
  			<div class="form">
  				<form action="/user/<?php print $data->user->uid; ?>/whiteboard/add" enctype="multipart/form-data" method="post">
  					<textarea columns="60" name="content" placeholder="What's new in your world?" rows="3"></textarea>
  					<?php if (in_array('can_upload_media', array_values($user->roles))) { ?>
  						<span class="file"></span>
  						<span class="button" href="#">
  							<span>Add Media</span>
  							<input name="files[media]" type="file" />
  						</span>
  					<?php } ?>
  					<input type="hidden" name="type" value="<?php print arg(2) ? arg(2) : ($user->user_type == 'School Administrator' ? 'School' : ''); ?>" />
  					<input type="hidden" name="content_id" value="<?php print (arg(2) !='friends')?arg(3):''; ?>" />
  					<input type="hidden" name="dest" value="<?php print $_GET['q']; ?>"/>
  					<button class="button" type="submit">Post</button>
  				</form>
  			</div>
  		</div>
<?php } ?>
  	<div class="items">
  		<?php foreach($data->items as $item) { ?>
  			<?php if ($item->status == 1 || $item->user->uid == $user->uid) { ?>
  				<div class="item<?php print ($item->status == 0)? ' private' : ''; ?>">
  					<div class="avatar">
  						<img src="<?php print v2_profiles_avatars_query($item->user->uid); ?>" width="84" />
  					</div>
  					<div class="name">
  						<?php if ($user->uid == $item->user->uid) { ?>
  							<strong><a href="/user/<?php print $item->user->uid; ?>"><?php print $item->user->name; ?></a></strong>
  						<?php } else { ?>
  							<strong><a href="/user/<?php print $user->uid; ?>/friends/<?php print $item->user->uid; ?>"><?php print $item->user->name; ?></a></strong>
  						<?php } ?>
  					</div>

  					<?php if (!empty($item->image)) { ?>
  						<div class="media">
  							<img src="/<?php print imagecache_create_path('468x',str_replace('/sites/','sites/',$item->image)); ?>" width="468" />
  						</div>
  					<?php } ?>
  					<?php if (!empty($item->video) && !empty($item->video->field_viddler_id[0]['value'])) { ?>
  						<div class="media">
  							<object
  								classid="clsid:D27CDB6E-AE6D-11cf-96B8-444553540000"
  								height="305"
  								width="438">
  								<param name="movie" value="//www.viddler.com/mini/<?php print $item->video->field_viddler_id[0]['value']; ?>/"/>
  								<param name="allowScriptAccess" value="always"/>
  								<param name="allowNetworking" value="all"/>
  								<param name="allowFullScreen"value="true"/>
  								<param name="flashVars" value="f=1&amp;autoplay=f&amp;loop=0&amp;nologo=1&amp;hd=1&amp;wmode=transparent"/>
  								<param name="wmode" value="transparent"/>
  								<embed
  									allowFullScreen="true"
  									allowNetworking="all"
  									allowScriptAccess="always"
  									flashVars="f=1&amp;autoplay=f&amp;loop=0&amp;nologo=1&amp;hd=1&amp;wmode=transparent"
  									height="305"
  									src="//www.viddler.com/mini/<?php print $item->video->field_viddler_id[0]['value']; ?>/"
  									type="application/x-shockwave-flash"
  									width="468"
  									wmode="transparent"
  								></embed>
  							</object>
  						</div>
  					<?php } ?>

  					<div class="content">
  						<?php print $item->content; ?>
  						<div class="flag-wrapper">
                <?php print $item->flags_output;?>
    				   </div>
   					</div>
  					<?php foreach($item->comments as $comment) { ?>
  						<?php if ($comment->status == 1 || $comment->user->uid == $user->uid) { ?>
  							<div class="comment<?php print ($comment->status == 0)? ' private' : ''; ?>">
  								<div class="avatar">
  									<img src="<?php print v2_profiles_avatars_query($comment->user->uid); ?>" width="42" />
  								</div>
  								<div class="name">
  									<?php if ($user->uid == $comment->user->uid) { ?>
  										<strong><a href="/user/<?php print $comment->user->uid; ?>"><?php print $comment->user->name; ?></a></strong>
  									<?php } else { ?>
  										<strong><a href="/user/<?php print $user->uid; ?>/friends/<?php print $comment->user->uid; ?>"><?php print $comment->user->name; ?></a></strong>
  									<?php } ?>
  								</div>
  								<div class="content">
  									<?php print $comment->content; ?>
  								</div>
                  <div class="like-wrapper">
                    <?php
                      
                      
                        $users = array();
                        $flag = flag_get_flag('like_comment');
                        $flag_count = $flag->get_count($comment->id);
                        $flagmsg = t('Be the first to like this post!');
                  
                        $flaggers = db_query('SELECT u.uid, u.name FROM {flag_content} fc join {users} u on u.uid = fc.uid where content_type ="comment" and content_id = %d and fid = %d order by timestamp desc', array($comment->id, 13));//13 is flag id for like_comment
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
                            $flagmsg = implode(', ', (array_slice($users, 0, 3))) . ' and <em class="modal-tip" id="modal-tip-'.$comment->id.'">'. theme('item_list',array_slice($users,-2), null,'ul',array('class' => 'morelikes'), 'morelikes-' . $commet->id,'item-list-likes') . ($flag_count-3) . ' others liked this</em>';
                            break;
                        }
                  
                        if($data->readonly == false){
                          print flag_create_link('like_comment', $comment->id);                          
                        }

                        print '<span>&nbsp;&middot;&nbsp;' . $flagmsg. '</span>';
                                        

                      ?>
                  </div>
                  
                  <?php if ($data->readonly == false): ?>
    								<div class="actions">
    									<?php 
                        
      									if ($item->uid === $user->uid || $comment->user->uid === $user->uid) { ?>
    										<a class="delete" href="/user/<?php print $data->user->uid; ?>/whiteboard/<?php print $item->id; ?>/comments/<?php print $comment->id; ?>/delete" title="Remove this post">Delete</a>
    									<?php }
  
                      if($comment->user->uid != $user->uid){ ?>
    										<a class="report" href="/user/<?php print $data->user->uid; ?>/whiteboard/<?php print $item->id; ?>/comments/<?php print $comment->id; ?>/report" title="Report this post">Report</a>
    									<?php } ?>
    								</div>
                  <?php endif;?>
  							</div>

  						<?php } ?>
  					<?php } ?>

  					<?php if($data->readonly == false):?>
              <?php //print_r($data); ?>
  						<div class="form">
  							<form action="/user/<?php print arg(1);//print arg(1);//$data->user->uid; ?>/whiteboard/<?php print $item->id; ?>/comments/add" method="post">
  								<input name="content" placeholder="Comment..." type="text" />
  								<button class="button" type="submit">Post</button>
  							</form>
  						</div>
            
            <?php endif; ?>
  
    					<div class="actions">
    						<?php if ($data->user->uid === $user->uid || $item->user->uid === $user->uid) { ?>
    							<a class="delete" href="/user/<?php print $data->user->uid; ?>/whiteboard/<?php print $item->id; ?>/delete" title="Remove this post">Delete</a>
    						<?php } else { ?>
    							<a class="report" href="/user/<?php print $data->user->uid; ?>/whiteboard/<?php print $item->id; ?>/report" title="Report this post">Report</a>
    						<?php } ?>
    					</div>

  				</div>

  			<?php } ?>
  		<?php } ?>

  	</div>
  	
<?php if ($_SESSION['show_post_pending_moderation']) { unset($_SESSION['show_post_pending_moderation']); ?>

	<div class="block modal" id="post-pending-moderation" style="display:none;">
		<div class="section title">
			<h1>Your post will be available shortly.</h1>
		</div>
		<div class="section cms">
			<p>In the meantime this pre-post is available only for you to see.</p>
		</div>
	</div>

<?php } ?>  	