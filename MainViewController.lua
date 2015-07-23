waxClass{"MainViewController", UITableViewController}

function tableView_cellForRowAtIndexPath(self, tableView, indexPath)
	local cell = self:ORIGtableView_cellForRowAtIndexPath(tableView, indexPath)
	cell:textLabel():setText("" .. (10 - indexPath:row()))
	cell:detailTextLabel():setText("lalalaheiheihei")
	cell:textLabel():setTextColor(UIColor:blueColor())
	return cell
end
