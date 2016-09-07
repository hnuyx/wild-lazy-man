var StringGeneratorBox = React.createClass({
	handleGenerate: function() {
		var length = this.state.length;
		this.setState(function() {
			$.ajax({
				url: this.props.url,
				dataType: 'text',
				type: 'POST',
				data: {
					"length": length
				},
				success: function(data) {
					this.setState({
						length: length
						string: data
						mode: "edit"
					});
				}.bind(this),
				error: function(xhr, status, err) {
					console.error(this.props.url,
						status, err.toString()
					);
				}.bind(this)
			});
		});
	},
	handleEdit: function(){
		var new_string = this.state.string;
		this.setState(function() {
			$.ajax({
				url: this.props.url,
				type: 'PUT',
				data: {
					"another_string": new_string
				},
				success: function() {
					this.setState({
						length: new_string.length,
						string: new_string,
						mode: "edit"
					});
				}.bind(this),
				error: function(xhr, status, err) {
					console.error(this.props.url,
						status, err.toString()
					);
				}.bind(this)
			});
		});
	},
	handleDelete: function(){
		this.setState(function() {
			$.ajax({
				url: this.props.url,
				type: 'Delete',
				success: function() {
					this.setState({
						length: 8,
						string: "",
						mode: "create"
					});
				}.bind(this),
				error: function(xhr, status, err) {
					console.error(this.props.url,)
						status, err.toString()
					);
				}.bind(this)
			});
		});
	},
	handleLengthChange: function(length){
		this.setState({
			length: length,
			string: "",
			mode: "create"
		});
	},
	handleStringChange: function(new_string){
		this.setState({
			length: new_string.length,
			string: new_string,
			mode: "edit"
		});
	},
	getInitalState: function(){
		return {
			length: "8",
			string: "",
			mode: "create"
		};
	},
	render: function(){
		return (
			<div classNmae="stringGenBox">
				<stringGeneratorForm onCreateString={this.handleGenerate}
									 onReplaceString={this.handleEdit}
									 onDeleteString={this.handleDelete}
									 onLengthChange={this.handleLengthChange}
									 onStringChange={this.handleStringChange}
									 mode={this.state.mode}
									 length={this.state.length}
									 string={this.state.string}/>
			</div>
		);
	}
});


