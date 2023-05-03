#
#  Provider section

provider "aws" {
  profile    = "default"
  region     = "us-east-1"
}

# Create security group
resource "aws_security_group" "web_server_sg" {
  name_prefix = "web-server-sg"

  ingress {
    from_port   = 80
    to_port     = 80
    protocol    = "tcp"
    cidr_blocks = ["76.102.19.196/32"]
  }

  ingress {
    from_port   = 22
    to_port     = 22
    protocol    = "tcp"
    cidr_blocks = ["76.102.19.196/32"]
  }

  ingress {
    from_port   = 443
    to_port     = 443
    protocol    = "tcp"
    cidr_blocks = ["76.102.19.196/32"]
  }

  tags = {
    Name = "web-server-sg"
  }
}

# Create 2 EC2 instance
resource "aws_instance" "web_server" {
  count         = 2
  ami           = "ami-0c94855ba95c71c99"
  instance_type = "t2.micro"
  key_name      = "ins"
  security_groups = [aws_security_group.web_server_sg.name]

  tags = {
    Name = "web-server-${count.index + 1}"
  }


/*  Install apache2 on these instances */

  connection {
    type        = "ssh"
    user        = "ubuntu"
    private_key = file("~/.ssh/id_rsa")
    host        = self.public_ip
  }

  provisioner "remote-exec" {
    inline = [
      "sudo apt-get update",
      "sudo apt-get install -y apache2"
    ]
  }
}

/* End of package installation */


/******************************

   Create a Elastic IP 
*******************************/


# Create Elastic IP address
resource "aws_eip" "web_server_eip" {
  vpc = true
}

# Associate Elastic IP address with first instance
resource "aws_eip_association" "web_server_eip_association" {
  instance_id   = aws_instance.web_server.0.id
  allocation_id = aws_eip.web_server_eip.id
}

