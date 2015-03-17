<div class="block shadow teacher-class friends browse">

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

	<div class="content">
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