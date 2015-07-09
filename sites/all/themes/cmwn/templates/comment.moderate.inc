<?php
  //$node_user = user_load($node->field_user_reference[0]['uid']);
  global $user;
?>

<div id="v2">
  <div class="block whiteboard index">
    <div id="whiteboard-profile-tabs">
      <div id="whiteboard-tab">
        <div class="items">
          <div class="item">
            <div class="avatar">
              <img src="<?php print v2_profiles_avatars_query($comment->uid);?>" width="84">
            </div>
            <div class="name">
                <strong><a href="/user/<?php print $comment->uid; ?>"><?php print $node_user->name; ?></a></strong><br />
                <em><?php print format_interval(time() - $comment->timestamp) . ' ago'; ?></em>
            </div>
  
            
            <div class="content">
              <?php
                print $comment->comment;
              ?>
            </div>
            <div class="actions">
              <a class="delete" href="#" title="close this post without taking any action" onclick="jQuery(this).parents('tr').remove();"></a>
            </div>      
          </div>
          <?php if(in_array('moderator', $user->roles) && $_GET['mod'] == 'process' ):?>
            <div class="mod-actions">
              
              <div class="mod-deny-form">
                <a href="#" class="mod-deny-post">Deny Comment</a>
                <?php 
                  print drupal_get_form("cmwn_moderation_form");
                ?>
              </div>
              
              <a href="/node/<?php print $node->nid; ?>/approve?destination=mod" class="mod-approve-post">Approve Comment</a>    
              <a href="#" class="mod-send-to-supervisor">or send to supervisor for review</a>
              
            </div>
          <?php endif;?>          
        </div>
      </div>          
    </div>
  </div>
</div>
