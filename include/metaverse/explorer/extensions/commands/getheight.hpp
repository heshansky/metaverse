/**
 * Copyright (c) 2016-2017 mvs developers 
 *
 * This file is part of metaverse-explorer.
 *
 * metaverse-explorer is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Affero General Public License with
 * additional permissions to the one published by the Free Software
 * Foundation, either version 3 of the License, or (at your option)
 * any later version. For more information see LICENSE.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */


#include <metaverse/explorer/extensions/command_extension.hpp>
#include <metaverse/explorer/extensions/node_method_wrapper.hpp>

namespace libbitcoin {
namespace explorer {
namespace commands {


/************************ getheight *************************/

class getheight: public command_extension
{
public:
    getheight() noexcept {};
    getheight(const std::string& other){ if (other == "fetch-height") option_.is_fetch_height = true; }

    static const char* symbol(){ return "getheight";}
    const char* name() override { return symbol();} 
    const char* category() override { return "EXTENSION"; }
    const char* description() override { return "Get last height."; }

    arguments_metadata& load_arguments() override
    {
        return get_argument_metadata()
            .add("ADMINNAME", 1)
            .add("ADMINAUTH", 1);
    }

    void load_fallbacks (std::istream& input, 
        po::variables_map& variables) override
    {
        const auto raw = requires_raw_input();
        load_input(auth_.name, "ADMINNAME", variables, input, raw);
        load_input(auth_.auth, "ADMINAUTH", variables, input, raw);
    }

    options_metadata& load_options() override
    {
        using namespace po;
        options_description& options = get_option_metadata();
        options.add_options()
		(
            BX_HELP_VARIABLE ",h",
            value<bool>()->zero_tokens(),
            "Get a description and instructions for this command."
        )
	    (
            "ADMINNAME",
            value<std::string>(&auth_.name),
            BX_ADMIN_NAME
	    )
        (
            "ADMINAUTH",
            value<std::string>(&auth_.auth),
            BX_ADMIN_AUTH
	    );

        return options;
    }

    void set_defaults_from_config (po::variables_map& variables) override
    {
    }

    console_result invoke (std::ostream& output,
        std::ostream& cerr, libbitcoin::server::server_node& node) override;

    struct argument
    {
    } argument_;

    struct option
    {
        bool is_fetch_height{false};
    } option_;

};


} // namespace commands
} // namespace explorer
} // namespace libbitcoin

