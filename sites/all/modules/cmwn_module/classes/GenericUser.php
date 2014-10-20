<?php


class GenericUser {
  
  public $uid;
  public $name;
  
  protected $_baseProfile;
  
  public function __construct($obj) {
    foreach (get_object_vars($obj) as $key => $val) {
      $this->{$key} = $val;
    }
    $this->_baseProfile = content_profile_load('base_profile', $this->uid);
  }
  
  public function getBaseProfile() {
    return $this->_baseProfile;
  }
  
  /**
   * 
   * Enter description here ...
   * @param unknown_type $obj
   * @return GenericUser
   */
  public static function castAs($obj) {
    if ($obj instanceof GenericUser) {
      return $obj;
    }
    return new GenericUser($obj);
  }
  
  public function getAvatar($render = false) {
    $profile = $this->getBaseProfile();
    if ($profile) {
      $avatar = node_load($profile->field_avatar_reference[0]['nid']);
      if ($avatar) {
        if ($render) {
          return '<div class="avatar_small">'.theme('imagecache', 'avatar_small', $avatar->field_avatar[0]['filepath']).'</div>';
        } else {
          return $avatar;
        }
      }
    }
    return false;
  }
  
  public function getProjects($full = false) {
      $sql = <<<EOSQL
SELECT
n.nid,
n.title as project_title,
n3.title AS brand_partner_title,
n3.nid AS brand_partner_nid,
(SELECT n2.status FROM {og_ancestry} oa INNER JOIN {node} n2 ON oa.nid = n2.nid WHERE oa.group_nid = n.nid AND n2.status = 1 AND n2.uid = %d) AS is_complete
FROM {node} n
INNER JOIN {og_uid} ou ON ou.nid = n.nid
INNER JOIN {content_type_project} ctp ON ctp.nid = n.nid
INNER JOIN {content_type_brand_partner} ctbp on ctbp.nid = ctp.field_brand_partner_nid
INNER JOIN {node} n3 ON n3.nid = ctbp.nid
WHERE n.type = 'project'
AND ou.uid = %d
EOSQL;
    $projects = array();
    $result = db_query($sql, $this->uid, $this->uid);
    while ($row = db_fetch_object($result)) {
      if ($full) {
        $obj = array('project' => node_load($row->nid), 'partner' => node_load($row->brand_partner_nid));
        $obj['project']->is_complete = $row->is_complete;
        $projects[] = $obj;
      } else {
        $projects[] = $row;
      }
    }
    return $projects;
  }
  
}