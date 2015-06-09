<div class="block shadow whiteboard index teacher-class friends browse" id="whiteboard-profile-tabs">

  <ul class="header">
    <li class="section">
      <a href="#whiteboard-tab"><h2>Whiteboard</h2></a>
    </li>

    <li class="section">
      <a href="#class-tab" class="tab-class"><h2>My Class</h2></a><span class="call-monitor" title="Call a Monitor"></span>
    </li>
  </ul>

  <div id="whiteboard-tab">
    <?php if ($user->user_type == 'child' || $user->user_type == 'teacher') { ?>
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
            <button class="button" type="submit">Post</button>
          </form>
        </div>
      </div>
    <?php } ?>
  </div>
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
                  width="438"
                >
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
                    $rndswitch = rand(0,1);
                    $random_users = db_query('select name from {users} order by RAND() limit 4');
                    $users = array();
                    while ($r = db_fetch_array($random_users)){
                      $users[] = $r['name'];
                    }

                    $flag = flag_get_flag('like_comment');
                    $flags = $flag->get_count($item->nid);
                    $flagmsg = t('Be the first to like this comment!');
                    switch (true){
                      case $flags < 3 && $flags > 0:
                        $flagmsg = implode(', ',$users) .' and <em class="modal-tip">'.$flags.' others liked this</em>';
                        break;
                      case 0:
                        break;
                      default: // a few flags less than three
                        $flagmsg = implode(', ',$users) .'<em> liked this</em>';
                        break;
                    }
                    print flag_create_link('like_comment', $comment->id);
                    print '<span>&nbsp;&middot;&nbsp;' . $flagmsg. '</span>';

                    ?>
                  </div>
                  <div class="actions">
                    <?php if ($data->user->uid === $user->uid || $comment->user->uid === $user->uid) { ?>
                      <a class="delete" href="/user/<?php print $data->user->uid; ?>/whiteboard/<?php print $item->id; ?>/comments/<?php print $comment->id; ?>/delete" title="Remove this post">Delete</a>
                    <?php }

                    if($comment->user->uid != $user->uid){ ?>
                      <a class="report" href="/user/<?php print $data->user->uid; ?>/whiteboard/<?php print $item->id; ?>/comments/<?php print $comment->id; ?>/report" title="Report this post">Report</a>
                    <?php } ?>
                  </div>

                </div>

              <?php } ?>
            <?php } ?>

            <?php //if ($user->user_type == 'child') {//????? ?>

              <div class="form">
                <form action="/user/<?php print $data->user->uid; ?>/whiteboard/<?php print $item->id; ?>/comments/add" method="post">
                  <input name="content" placeholder="Comment..." type="text" />
                  <button class="button" type="submit">Post</button>
                </form>
              </div>

            <?php //} ?>

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

  <div id="class-tab">
    <?php if(false):?>
    	<div class="header">

    		<div class="section">
    			<h2>Your Class: <?php print sizeof($data->students); ?></h2>
    		</div>

    		<?php if ($user->uid === $data->user->uid) { ?>
    			<div class="section form">
    				<form action="/user/<?php print $data->user->uid; ?>/friends/search" method="post">
    					<input name="q" placeholder="Search Class" type="text" />
    					<button class="button" type="submit">Go!</button>
    				</form>
    			</div>
    		<?php } ?>

    	</div>
    <?php endif;?>
  	<div class="content">
      <h6><?php print $data->class->title;?></h6>
  		<div class="section grid">
  			<?php if (sizeof($data->students) > 0) { ?>
  				<div class="items">
  					<?php foreach ($data->students as $item) { ?>
  						<?php
  							if ($user->uid === $data->user->uid) {
  								$href = '/user/' . $data->user->uid . '/friends/' . $item->uid;
  							} else {
  								if ($user->uid === $item->uid) {
  									$href = '/user';
  								} else {
  									$href = '/user/' . $user->uid . '/friends/' . $item->uid;
  								}
  							}
              ?>
  						<div class="item">
  							<div class="image">
  								<a href="<?php print $href; ?>"><img height="126" src="<?php print $item->avatar; ?>" width="126" /></a>
  							</div>
  							<div class="name">
  								<a href="<?php print $href; ?>"><?php print $item->name; ?></a>
  								<span><?php print $item->total_earned_flips; ?> Flips Earned</span>
  							</div>
  							<?php if($item->total_earned_flips > 0):?>
    							<div class="student-flips description block modal flips" id="flips-<?php print $item->uid;?>">
      						  <h2><?php print $item->name; ?>'s Flips</h2>
                    <?php
                      foreach($item->flips as $flip){
                        if($flip->progress == '100'){
                          print '<div class="student-flip">';
                          print '<img src="'.$flip->src2.'" class="student-flip-img student-flip-img-left-link" />';
                            print '<div class="student-flip-right">';
                              print $flip->title .'<br />';
                              //find date of last submission
                              $flip_node = node_load($flip->id);
                              $finish_nid = $flip_node->field_actions[count($flip_node->field_actions) - 1]['nid'];
                              $submissions = webform_get_submissions(array('nid' => $finish_nid, 'uid' => $item->uid));
                              if(is_array($submissions)){
                                $submission = array_shift($submissions);
                                print '<em> Earned ' . (date('F dS, Y',$submission->submitted)) . '</em>';
                              }
                            print '</div>';
                          print '</div>';
                        }
                      }
                    ?>
    							</div>
                <?php else:?>
                  <div class="student-flips description block modal flips" id="flips-<?php print $item->uid;?>">
                      <h2><?php print $item->name; ?> has no Flips yet.</h2>
                  </div>
    						<?php endif;?>
  						</div>
  					<?php } ?>
  				</div>
  			<?php } else { ?>
  				<p>There are no classmates.</p>
  			<?php } ?>
  		</div>
  	</div>
  </div>
</div>
