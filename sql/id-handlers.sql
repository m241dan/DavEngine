SET FOREIGN_KEY_CHECKS=0;

DROP TABLE IF EXISTS `id-handlers`;
CREATE TABLE IF NOT EXISTS `id-handlers` (
   `type` smallint NOT NULL DEFAULT '-1',
   `name` varchar(20) NOT NULL DEFAULT 'unknown',
   `top_id` int NOT NULL DEFAULT '-1',
   `can_recycle` smallint NOT NULL DEFAULT '0',
   PRIMARY KEY (`type`),
   UNIQUE INDEX `name` (`name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;


INSERT INTO `id-handlers` VALUES ( '0', 'Account Handler', '0', '0' );
INSERT INTO `id-handlers` VALUES ( '1', 'Workspace Handler', '0', '1' );
